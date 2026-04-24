const dns: typeof import("dns") = require("dns");

dns.lookup("google.com", (err: NodeJS.ErrnoException | null, address: string, family: number) => {
  if (err) {
    console.log("dns lookup failed:", err.message);
  } else {
    console.log("resolved google.com:", address, "family:", family);
  }
});
