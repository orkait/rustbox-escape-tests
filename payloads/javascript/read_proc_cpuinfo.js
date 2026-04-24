const fs = require("fs");
const data = fs.readFileSync("/proc/cpuinfo", "utf8");
console.log(data);
