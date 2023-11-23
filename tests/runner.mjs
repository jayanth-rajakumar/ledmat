const red    = s => `\x1b[31m${s}\x1b[0m`;
const green  = s => `\x1b[32m${s}\x1b[0m`;
const yellow = s => `\x1b[33m${s}\x1b[0m`;

const t = {
	tap: x => {
		console.error("tap:", x);
		return x;
	},
	start: msg => {
		console.error(`${msg}:`);
	},
	test: (msg, fn) => {
		try {
			fn();
			console.error(`${yellow("testing")}: ${msg}... ${green("OK")}`);
		} catch (e) {
			console.error(`${yellow("testing")}: ${msg}... ${red("FAIL")}`);
			throw e;
		}
	},
};

export const runTests = async tests => {
	for (const testFn of tests) {
		await testFn(t);
	}
};
