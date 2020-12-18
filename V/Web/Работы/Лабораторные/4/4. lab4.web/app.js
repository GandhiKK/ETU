const express = require('express');
const router = require('./router').router;
const createDomain = require('domain');
const bodyParser = require('body-parser');
const cookieParser = require('cookie-parser');

let domain = createDomain.create(), server;

domain.on("error", (err) => {
    console.log("Домен перехватил ошибку %s", err);
});

domain.run(() => {
    server = express();
});

server.use(cookieParser());
server.use(bodyParser.json());
server.use(bodyParser.urlencoded({extended: true}));
server.use('/public', express.static('public'));
server.use("", router);

server.set("view engine", "pug");
server.set("views", `./views`);

server.listen(3000);
