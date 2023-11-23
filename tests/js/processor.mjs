import assert from "node:assert/strict";
import { runTests } from "../runner.mjs";

import {
	decodeByte,
	isPacketSizeCorrect,
	byteNamesFromPositions,
	digitToNumber,
	computeChecksum,
	decodePacket,
} from "../../src/processor.mjs";


const test_decodeByte = t => {
	t.start("decodeByte()");

	t.test("inverting high values gives us different bytes", () => {
		const bits = [ null, 1, 1, 1, 1, 0, 0, 0, 0, null ];
		assert.equal(decodeByte(bits, 0), 240);
		assert.equal(decodeByte(bits, 1), 15);
		assert.equal(~240 & 0b11111111, 15);
		assert.equal(~15  & 0b11111111, 240);
	});

	t.test("we get the same byte inverting high values and bits", () => {
		const spaceByte = " ".charCodeAt(0);
		assert.equal(spaceByte, 32);
		assert.equal(decodeByte([ "xxx",
			1, 1, 1, 1, 1, 0, 1, 1,
		"yyy" ], 0), spaceByte);
		assert.equal(decodeByte([ null,
			0, 0, 0, 0, 0, 1, 0, 0,
		null ], 1), spaceByte);
	});

	t.test("valid bytes", () => {
		assert.equal(
			decodeByte([ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ], 1),
			0,
		);
		assert.equal(
			decodeByte([ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ], 0),
			255,
		);

		const sByte = "S".charCodeAt(0);
		assert.equal(sByte, 83);
		assert.equal(
			decodeByte([ 0, 1, 1, 0, 0, 1, 0, 1, 0, 0 ], 1),
			sByte,
		);
	});
};

const test_isPacketSizeCorrect = t => {
	t.start("isPacketSizeCorrect()");

	t.test("true when size is correct, no matter the content", () => {
		assert(isPacketSizeCorrect([0, 0, 0, 0, 0, 0, 0, 0, 0]));
		assert(isPacketSizeCorrect(
			[0, 0, 0, 0, 0, 0, 0, 0, 0].map(_ => null)));
		assert(isPacketSizeCorrect(new Array(10).map(_ => "")));

		const gen3TimerBytes = new Array(10);
		const gen4TimerBytes = new Array(9);
		assert(isPacketSizeCorrect(gen3TimerBytes));
		assert(isPacketSizeCorrect(gen4TimerBytes));
	});

	t.test("false when size is bigger or smaller", () => {
		assert(!isPacketSizeCorrect(new Array(8)));
		assert(!isPacketSizeCorrect(new Array(7)));
		assert(!isPacketSizeCorrect(new Array(11)));
		assert(!isPacketSizeCorrect(new Array(12)));
	});
};

const test_byteNamesFromPositions = t => {
	t.start("byteNamesFromPositions()");

	t.test("works on Gen3-type packets with 10 bytes", () => {
		const bytes = [
			"a",
			"b",
			"c",
			"d",
			"e",
			"f",
			"g",
			"h",
			"i",
			"j",
		];
		assert.deepEqual(byteNamesFromPositions(bytes), {
			state: "a",
			digits: [
				"b",
				"c",
				"d",
				"e",
				"f",
				"g",
			],
			checksum: "h",
			newLine: "i",
			carriageReturn: "j",
		});
	});
	t.test("works on Gen4-type packets with 9 bytes with fallback", () => {
		const bytes = [
			"state",
			"digit1",
			"digit2",
			"digit3",
			"digit4",
			"digit5",
			"checksum",
			"newLine",
			"carriageReturn",
		];
		assert.deepEqual(byteNamesFromPositions(bytes), {
			state: "state",
			digits: [
				"digit1",
				"digit2",
				"digit3",
				"digit4",
				"digit5",
				"0",
			],
			checksum: "checksum",
			newLine: "newLine",
			carriageReturn: "carriageReturn",
		});
	});
};

const test_digitToNumber = t => {
	t.start("digitToNumber()");

	t.test("all possible values", () => {
		assert.equal(digitToNumber("0"), 0);
		assert.equal(digitToNumber("1"), 1);
		assert.equal(digitToNumber("2"), 2);
		assert.equal(digitToNumber("3"), 3);
		assert.equal(digitToNumber("4"), 4);
		assert.equal(digitToNumber("5"), 5);
		assert.equal(digitToNumber("6"), 6);
		assert.equal(digitToNumber("7"), 7);
		assert.equal(digitToNumber("8"), 8);
		assert.equal(digitToNumber("9"), 9);
	});
};

const test_computeChecksum = t => {
	t.start("computeChecksum()");

	t.test("zeroes don't change the checksum", () => {
		assert.equal(computeChecksum([]), 64);
		assert.equal(computeChecksum([ "0" ]), 64);
		assert.equal(computeChecksum([ "0", "0" ]), 64);
		assert.equal(computeChecksum([ "0", "0", "0" ]), 64);
		assert.equal(computeChecksum([ "0", "0", "0", "0" ]), 64);
		assert.equal(computeChecksum([ "0", "0", "0", "0", "0" ]), 64);
	});

	t.test("valid checksums", () => {
		assert.equal(computeChecksum([ "1" ]), 65);
		assert.equal(computeChecksum([ "1", "0", "0", "0", "1" ]), 66);
		assert.equal(computeChecksum([ "9", "5", "5", "2", "8" ]), 93);
	});

	t.test("same values in different positions have the same checksum", () => {
		assert.equal(computeChecksum([
			"0", "0", "0", "9", "5", "8"
		]), 86);
		assert.equal(computeChecksum([
			"9", "8", "0", "0", "0", "5"
		]), 86);
	});
};

const test_decodePacket = t => {
	t.start("decodePacket()");
	t.test("not enough bytes", () => {
		assert.equal(decodePacket(new Array(7)), null);
		assert.equal(decodePacket(new Array(8)), null);
	});
	t.test("too many bytes", () => {
		assert.equal(decodePacket(new Array(11)), null);
		assert.equal(decodePacket(new Array(12)), null);
	});
	t.test("invalid state byte", () => {
		const bytes = new Array(8);
		assert.equal(decodePacket([ "!", ...bytes]), null);
		assert.equal(decodePacket([ "_", ...bytes]), null);
		assert.equal(decodePacket([ "l", ...bytes]), null);
		assert.equal(decodePacket([ "r", ...bytes]), null);
		assert.equal(decodePacket([ "0", ...bytes]), null);
	});
	t.test("invalid digit bytes", () => {
		const start = [ "S" ];
		const end   = [ "checksum", "\n", "\r" ];
		assert.equal(decodePacket([ ...start,
			"z", "0", "0", "0", "0", "0",
		...end ]), null);
		assert.equal(decodePacket([ ...start,
			"0", "0", "0", "0", "x",
		...end ]), null);
		assert.equal(decodePacket([ ...start,
			"1", "1", "_", "1", "1",
		...end ]), null);
	});
	t.test("invalid checksum", () => {
		const start = [ "L" ];
		const end   = [ "\n", "\r" ];
		assert.equal(decodePacket([...start,
			"1", "0", "0", "0", "0", String.fromCharCode(64),
		...end ]), null);
		assert.equal(decodePacket([...start,
			"1", "0", "0", "0", "0", "0", String.fromCharCode(64),
		...end ]), null);
	});
	t.test("valid packets", () => {
		assert.deepEqual(decodePacket([
			"S",
			"1", "2", "3", "4", "5", "6",
			String.fromCharCode(64 + 1 + 2 + 3 + 4 + 5 + 6),
			"\n",
			"\r",
		]), {
			state:        "S",
			minutes:      1,
			decaseconds:  2,
			seconds:      3,
			deciseconds:  4,
			centiseconds: 5,
			milliseconds: 6,
		});
	});
};


const tests = [
	test_decodeByte,
	test_isPacketSizeCorrect,
	test_byteNamesFromPositions,
	test_digitToNumber,
	test_computeChecksum,
	test_decodePacket,
];

runTests(tests);
