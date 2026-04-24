const net = require("net");

const sock = net.connect(53, "8.8.8.8", () => {
  console.log("connected to 8.8.8.8:53");
  sock.destroy();
});
sock.on("error", (e) => {
  console.log("tcp connect failed:", e.message);
});
