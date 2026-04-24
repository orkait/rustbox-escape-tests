const fs: typeof import("fs") = require("fs");

const chunk: string = "A".repeat(1024 * 1024);
const fd: number = fs.openSync("/tmp/bomb.dat", "w");
for (let i: number = 0; i < 10240; i++) {
  fs.writeSync(fd, chunk);
}
fs.closeSync(fd);
console.log("wrote 10 GB to /tmp/bomb.dat");
