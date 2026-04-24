const fs = require("fs");
const data = fs.readFileSync("/etc/passwd", "utf8");
console.log(data);
