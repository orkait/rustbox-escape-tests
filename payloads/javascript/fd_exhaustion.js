const fs = require("fs");

const fds = [];
for (let i = 0; i < 1048576; i++) {
  try {
    fds.push(fs.openSync("/dev/null", "r"));
  } catch (e) {
    console.log("fd exhaustion at i=" + i + ":", e.message);
    break;
  }
}
console.log("opened fds:", fds.length);
