import { Hono } from "hono";
import { serveStatic } from "hono/bun";

const app = new Hono();

app.get("/", serveStatic({ root: "./public/" }));
app.get("/script.js", serveStatic({ path:"./public/script.js" }));
app.get("/style.css", serveStatic({ path:"./public/styles.css" }));
app.get("/bootstrap.css", serveStatic({ path:"./public/bootstrap.min.css" }));

console.log("Listening on 3000")
Bun.serve({
    port: 3000,
    fetch: app.fetch
})