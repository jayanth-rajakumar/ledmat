export const main = async () => {
	const stream = await navigator.mediaDevices.getUserMedia({
		audio: {
			optional: [{
				echoCancellation: false,
				noiseSuppression: false,
			}],
		},
	});

	const audioContext = new AudioContext({
		echoCancellation: false,
		noiseSuppression: false,
	});

	const microphone = audioContext.createMediaStreamSource(stream);
	await audioContext.audioWorklet.addModule("./worklet.mjs");
	const stackmatSignal = new AudioWorkletNode(audioContext, "LedmatWorklet");

	microphone.connect(stackmatSignal);
	stackmatSignal.connect(audioContext.destination);

	stackmatSignal.port.onmessage = event => {
		console.log({data});
		handle(event.data);
	};
};
