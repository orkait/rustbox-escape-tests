const fs: typeof import("fs") = require("fs");

try {
  const entries: string[] = fs.readdirSync("/sys");
  console.log("entries:", entries);
  for (const entry of entries) {
    try {
      const stat: import("fs").Stats = fs.statSync("/sys/" + entry);
      if (stat.isFile()) {
        const data: string = fs.readFileSync("/sys/" + entry, "utf8");
        console.log("/sys/" + entry + ":", data.slice(0, 256));
      }
    } catch (e) {}
  }
} catch (e: any) {
  console.log("read /sys failed:", e.message);
}
