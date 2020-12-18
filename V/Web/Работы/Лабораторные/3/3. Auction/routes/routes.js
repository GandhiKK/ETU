var express = require('express');
var bodyParser = require('body-parser');
var fs = require('fs');
var path = require('path');
var router = express.Router();
router.use(bodyParser.json());

var arts_json = require('../public/json/paint');
var person_json = require('../public/json/person');
var setting = require('../public/json/setting');


router.get('/', function(req,res,next) {
    res.render('pictures', {title:'Перечень картин', arts: arts_json});
});
router.get('/setting', function(req,res,next) {
    res.render('setting', {title:'Настройки', item: setting});
});
router.get('/participants', function(req,res,next) {
    res.render('participants', {title:'Участники', persons: person_json});
});

router.post('/editPicture/:num', function(req,res,next) {
    const id = req.params.num;
    for(value of arts_json)
        if(value.id == id) {
            value.name = req.body.redact_name;
            value.artist = req.body.redact_artist;
            value.price = req.body.redact_price;
            value.min = req.body.redact_min;
            value.max = req.body.redact_max;
        }
    fs.writeFile('public/json/paint.json', JSON.stringify(arts_json), () => { });
    res.redirect('/')
});

router.post('/deletePicture/:num', function(req,res,next) {
    const id = req.params.num;
    arts_json.forEach((v, i) => {
        if (v.id == id) {
            arts_json.splice(i, 1);
            res.redirect('/');
        }
    });
    fs.writeFile('public/json/paint.json', JSON.stringify(arts_json), () => { });
});

router.post('/newPicture/', function(req,res,next) {
    var id = 0;
    arts_json.forEach((v, i) => {
        id = i + 1;
    });
    arts_json.push({
        "id": id,
        "name": req.body.name,
        "artist": req.body.artist,
        "price": req.body.price,
        "min": req.body.min,
        "max": req.body.max,
        "pt":req.body.pt
    });
    fs.writeFile('public/json/paint.json', JSON.stringify(arts_json), (err) => {
        if(err) throw err
    });
    res.redirect('/');
});

router.post('/editPerson/:num', function(req,res,next) {
    const id = req.params.num;
    for(value of person_json)
        if(value.id == id) {
            value.name = req.body.redact_name;
            value.money = req.body.redact_money;
        }
    fs.writeFile('public/json/person.json', JSON.stringify(person_json), () => { });
    res.redirect('/participants')
});

router.post('/deletePerson/:num', function(req,res,next) {
    const id = req.params.num;
    person_json.forEach((v, i) => {
        if (v.id == id) {
            person_json.splice(i, 1);
            res.redirect('/participants');
        }
    });
    fs.writeFile('public/json/person.json', JSON.stringify(person_json), () => { });
    res.redirect('/participants')
});

router.post('/newPerson/', function(req,res,next) {
    var id = 0;
    person_json.forEach((v, i) => {
        id = i + 1;
    });
    person_json.push({
        "id": id,
        "name": req.body.name,
        "money": req.body.money,
        "pt":req.body.pt
    });
    fs.writeFile('public/json/person.json', JSON.stringify(person_json), () => { });

    res.redirect('/participants');
});

router.post('/changeSetting/', function(req,res,next) {
    setting.dt=req.body.dt;
    setting.tm=req.body.tm;
    setting.tmout=req.body.tmout;
    setting.tmtorg=req.body.tmtorg;
    setting.tminfo=req.body.tminfo;
    fs.readFile(path.join(__dirname,'..','public','json','setting.json'),function(err,content){
        if(err) throw err;
        var parseJson = JSON.parse(content);
        parseJson.dt = setting.dt;
        parseJson.tm = setting.tm;
        parseJson.tmout = setting.tmout;
        parseJson.tmtorg = setting.tmtorg;
        parseJson.tminfo = setting.tminfo;
        fs.writeFile(path.join(__dirname,'..','public','json','setting.json'),JSON.stringify(parseJson),function(err){
            if(err) throw err;
        })
    });
    res.redirect('/setting')
});






module.exports = router;