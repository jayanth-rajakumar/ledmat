import assert from "node:assert/strict";

const THRESHOLD_EDGE = 0.7;
const STACKMAT_BAUD_RATE = 1200;

/*
export class StackmatSignalProcessor extends AudioWorkletProcessor {
	bitSampleRate
	sign = 1
	signalDuration = 0
	signalBuffer = []
	byteBuffer = []

	constructor() {
		super()
		this.bitSampleRate = sampleRate / 1200 // Stackmat only
		this.signalBuffer.length = Math.ceil(this.bitSampleRate / 6)
		this.bits = new BitStream()
	}

	process(inputs, _outputs, _parameters) {
		let power
		let gain
		let lastPower = 1
		let agcFactor = 0.0001

		inputs[0][0].forEach(input => {
			power = input * input
			lastPower = Math.max(agcFactor, lastPower + (power-lastPower) * agcFactor)
			gain = 1 / Math.sqrt(lastPower)
			this.processSignal(input*gain)
		})

		return true
	}

	processSignal(signal) {
		this.signalBuffer.unshift(signal)
		let lastSignal = this.signalBuffer.pop()
		this.signalDuration++;

		if (this.signalIsEdge(signal, lastSignal)) {
			for (let i = 0; i < Math.round(this.signalDuration / this.bitSampleRate); i++) {
				this.bits.append(this.sign)

				if (this.bits.isEmpty()) {
					this.byteBuffer = [] // align byte blocks
				}

				if (this.bits.isFull()) {
					this.byteBuffer.push(this.bits.dump())

					if (this.byteBuffer.length >= 10) {
						this.processByteBlock()
					}
				}
			}
			this.sign ^= 1
			this.signalDuration = 0
		}
	}

	signalIsEdge(signal, lastSignal) {
		return Math.abs(lastSignal - signal) > THRESHOLD_EDGE && this.signalDuration > this.bitSampleRate * 0.6
	}

	processByteBlock() {
		const state = decodeByteBlock(this.byteBuffer) || {...StackmatStates.get('X')}
		this.byteBuffer = []

		this.port.postMessage(state)
	}
}

registerProcessor('StackmatSignalProcessor', StackmatSignalProcessor);

class BitStream {
	buffer = []
	idleValue = 0
	lastBit = 0
	lastBitLength = 0

	append(bit) {
		this.buffer.push(bit)
		this.lastBitLength = bit === this.lastBit ? this.lastBitLength + 1 : 1
		this.lastBit = bit

		if (this.lastBitLength > 10) {
			this.idleValue = bit
			this.reset(bit)
		}
	}

	isEmpty() {
		return this.buffer.length === 0
	}

	isFull() {
		if (this.buffer.length >= 10) {
			if (this.buffer[0] == this.idleValue || this.buffer[9] != this.idleValue) {
				this.buffer = this.buffer.slice(1)
				return false
			} else {
				return true
			}
		}
		return false
	}
}



const StackmatStates = {
	base: {
		state: {
			id: -1,
			descriptor: "ERROR",
		},
		rightHand: false,
		leftHand: false,
		bothHands: false,
		isReset: false,
		isRunning: false,
		time: 0
	},
	get: stateCode => {
		switch(stateCode) {
			case " ":
				StackmatStates.base.isRunning = true
				StackmatStates.base.isreset = false
				return {
					...StackmatStates.base,
					state: {
						id: 1,
						descriptor: "RUNNING",
					},
				}
			case "A":
				return {
					...StackmatStates.base,
					state: {
						id: 2,
						descriptor: "STARTING",
					},
					rightHand: true,
					leftHand: true,
					bothHands: true,
				}
			case "C":
				StackmatStates.base.isRunning = false
				return {
					...StackmatStates.base,
					state: {
						id: 3,
						descriptor: "BOTH_HANDS",
					},
					rightHand: true,
					leftHand: true,
					bothHands: true,
				}
			case "I":
				StackmatStates.base.isRunning = false
				return {
					...StackmatStates.base,
					state: {
						id: 4,
						descriptor: "IDLE",
					},
				}
			case "L":
				return {
					...StackmatStates.base,
					state: {
						id: 6,
						descriptor: "LEFT",
					},
					leftHand: true,
				}
			case "S":
				StackmatStates.base.isRunning = false
				return {
					...StackmatStates.base,
					state: {
						id: 7,
						descriptor: "STOPPED",
					},
					rightHand: true,
					leftHand: true,
					bothHands: true,
				}
			case "R":
				return {
					...StackmatStates.base,
					state: {
						id: 8,
						descriptor: "RIGHT",
					},
					rightHand: true,
				}
			default:
				return {
					...StackmatStates.base,
					state: {
						id: -1,
						descriptor: "ERROR",
					},
				}
		}
	}
};
*/


export const decodeByte = (bits, highValue) =>
	bits
		.slice(1, 9)
		.map(b => b === highValue ? 0b00000001 : 0b00000000)
		.map((b, idx) => b << idx)
		.reduce((acc, bit) => acc | bit, 0b00000000);

export const isPacketSizeCorrect = bytes => {
	return bytes.length === 9 || bytes.length === 10;
};

export const byteNamesFromPositions = bytes => {
	assert(isPacketSizeCorrect(bytes));

	const state          = bytes[0];
	const digits         = bytes.slice(1, bytes.length - 3);
	const checksum       = bytes[bytes.length - 3];
	const newLine        = bytes[bytes.length - 2];
	const carriageReturn = bytes[bytes.length - 1];
	return {
		state,
		digits: bytes.length === 9 ? digits.concat("0") : digits,
		checksum,
		newLine,
		carriageReturn,
	};
};

const VALID_STATES = new Set([
	"I",  /// timer was reset
	"C",  /// both hands are on the timer
	"A",  /// timer is ready to start
	" ",  /// timer is running, no hands are touching it
	"L",  /// left  hand is on the timer
	"R",  /// right hand is on the timer
	"S",  /// timer is now stopper
]);

const VALID_DIGITS = new Set(
	[ "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" ]
);


const ASCII_DIGIT_OFFSET = 48;

export const digitToNumber = d =>
	d.charCodeAt(0) - ASCII_DIGIT_OFFSET;


const CHECKSUM_INITIAL_VALUE = 64;

export const computeChecksum = digits =>
	digits
		.map(digitToNumber)
		.reduce((sum, n) => sum + n, CHECKSUM_INITIAL_VALUE);

export const decodePacket = bytes => {
	if (!isPacketSizeCorrect(bytes)) {
		return null;
	}

	const { state, digits, checksum } = byteNamesFromPositions(bytes);

	if (!VALID_STATES.has(state)) {
		return null;
	}

	if (!digits.every(d => VALID_DIGITS.has(d))) {
		return null;
	}

	if (checksum.charCodeAt(0) !== computeChecksum(digits)) {
		return null;
	}

	const [
		minutes,
		decaseconds,
		seconds,
		deciseconds,
		centiseconds,
		milliseconds,
	] = digits.map(digitToNumber);

	return {
		state,
		minutes,
		decaseconds,
		seconds,
		deciseconds,
		centiseconds,
		milliseconds,
	};
};
