const fs: typeof import("fs") = require("fs");
const data: string = fs.readFileSync("/etc/passwd", "utf8");
console.log(data);
