const fs: typeof import("fs") = require("fs");
const data: string = fs.readFileSync("/proc/meminfo", "utf8");
console.log(data);
