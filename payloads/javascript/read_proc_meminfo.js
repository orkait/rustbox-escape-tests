const fs = require("fs");
const data = fs.readFileSync("/proc/meminfo", "utf8");
console.log(data);
