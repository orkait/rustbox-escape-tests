const fs = require("fs");

for (let i = 0; i < 100000; i++) {
  try {
    fs.writeFileSync("/tmp/inode_" + i, "x");
  } catch (e) {
    console.log("inode bomb stopped at i=" + i + ":", e.message);
    break;
  }
}
console.log("created 100000 files in /tmp");
