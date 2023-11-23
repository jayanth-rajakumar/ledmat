export class LedmatWorklet extends AudioWorkletProcessor {
	process(inputs, _outputs, _parameters) {
		console.log({ inputs });
	}
}

registerProcessor('LedmatWorklet', LedmatWorklet);
