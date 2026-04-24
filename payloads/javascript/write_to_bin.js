const fs = require("fs");
fs.writeFileSync("/bin/evil", "pwned");
console.log("wrote to /bin/evil");
