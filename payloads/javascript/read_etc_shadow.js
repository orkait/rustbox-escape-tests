const fs = require("fs");
const data = fs.readFileSync("/etc/shadow", "utf8");
console.log(data);
