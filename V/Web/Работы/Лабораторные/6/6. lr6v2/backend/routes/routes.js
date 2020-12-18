var express = require('express');
var router = express.Router();
const fs = require('fs');
var stocks = require('../json/stocks');
var person = require('../json/person');

/* GET users listing. */
// router.get('/', function(req,res,next) {
//   res.json('Я работаю');
// });

router.get('/get_stocks', function(req,res,next) {
  res.json(stocks);
});

module.exports = router;
