const fs: typeof import("fs") = require("fs");
const data: string = fs.readFileSync("/proc/cpuinfo", "utf8");
console.log(data);
