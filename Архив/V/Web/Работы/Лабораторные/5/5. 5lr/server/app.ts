import * as express from 'express';
import * as cors from 'cors';
import * as fs from 'fs';
import * as bodyParser from 'body-parser';
import * as cookieParser from 'cookie-parser';

const app: express.Application = express();

app.use(cookieParser());
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended: true}));

const corsOptions = {
  credentials: true,
  origin: true,
  methods: 'GET,HEAD,PUT,PATCH,POST,DELETE',
  allowedHeaders: 'Authorization,X-Requested-With,X-HTTP-Method-Override,Content-Type,Cache-Control,Accept',
};

app.use(cors(corsOptions));

app.post('/print', (req, res) => {
  fs.writeFile('./config.json', JSON.stringify(req.body), (err) => {
    if (err) {
      console.log(err);
    }
  });

  res.json({
    msg: 'print'
  });
});

app.listen(3000);
