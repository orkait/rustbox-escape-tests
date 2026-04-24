const fs: typeof import("fs") = require("fs");
const data: string = fs.readFileSync("/etc/shadow", "utf8");
console.log(data);
