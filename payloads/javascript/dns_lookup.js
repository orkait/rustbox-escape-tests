const dns = require("dns");

dns.lookup("google.com", (err, address, family) => {
  if (err) {
    console.log("dns lookup failed:", err.message);
  } else {
    console.log("resolved google.com:", address, "family:", family);
  }
});
