const assert = require("assert");
const should = require("should");
let tested = require("../router");

describe("var", () => {
    it("test №1", () => {
        parseInt(tested.lastIdArtInAuction).should.be.type('number');
        parseInt(tested.timeout).should.be.type('number');
        parseInt(tested.interval).should.be.type('number');
        parseInt(tested.pause).should.be.type('number');
    });

    it("test №2", () => {
        tested.config.should.have.property("paints");
        tested.config.should.have.property("partners");
        tested.config.should.have.property("config");
    });
});
