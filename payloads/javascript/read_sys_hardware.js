const fs = require("fs");

try {
  const entries = fs.readdirSync("/sys");
  console.log("entries:", entries);
  for (const entry of entries) {
    try {
      const stat = fs.statSync("/sys/" + entry);
      if (stat.isFile()) {
        const data = fs.readFileSync("/sys/" + entry, "utf8");
        console.log("/sys/" + entry + ":", data.slice(0, 256));
      }
    } catch (e) {}
  }
} catch (e) {
  console.log("read /sys failed:", e.message);
}
