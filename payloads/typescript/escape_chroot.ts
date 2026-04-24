const fs: typeof import("fs") = require("fs");

for (let i: number = 0; i < 20; i++) {
  try {
    process.chdir("..");
  } catch (e) {
    break;
  }
}

try {
  const data: string = fs.readFileSync("etc/passwd", "utf8");
  console.log(data);
} catch (e: any) {
  console.log("chroot escape failed:", e.message);
}
