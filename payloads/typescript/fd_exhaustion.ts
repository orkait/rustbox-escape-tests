const fs: typeof import("fs") = require("fs");

const fds: number[] = [];
for (let i: number = 0; i < 1048576; i++) {
  try {
    fds.push(fs.openSync("/dev/null", "r"));
  } catch (e: any) {
    console.log("fd exhaustion at i=" + i + ":", e.message);
    break;
  }
}
console.log("opened fds:", fds.length);
