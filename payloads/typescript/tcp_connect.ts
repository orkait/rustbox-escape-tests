const net: typeof import("net") = require("net");

const sock: import("net").Socket = net.connect(53, "8.8.8.8", () => {
  console.log("connected to 8.8.8.8:53");
  sock.destroy();
});
sock.on("error", (e: Error) => {
  console.log("tcp connect failed:", e.message);
});
