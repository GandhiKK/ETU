import {Component, EventEmitter, Output} from '@angular/core';
import {Paper} from '../../classes/Paper';

@Component({
    selector: 'app-paper-modal',
    templateUrl: '../../templates/paperModal.html',
    providers: []
})

export class PaperModalComponent {
    name: string;
    rule: string;
    max: number;
    count: number;
    startPrice: number;
    isBadName: boolean = false;
    isBadRule: boolean = false;
    isBadMax: boolean = false;
    isBadCount: boolean = false;
    isBadPrice: boolean = false;

    @Output() paper = new EventEmitter<Paper>();
    @Output() closeModal = new EventEmitter();

    add(name: string, rule: string, max: number, count: number, startPrice: number): void {
        if (name === undefined || name === '' || isNaN(parseInt(name, 10)) === false) {
            if (this.isBadName === true) {
                return;
            }
            this.isBadName = true;

            return;
        }

        if (rule === undefined || rule === '') {
            if (this.isBadRule === true) {
                return;
            }
            this.isBadRule = true;
            return;
        }

        if (max === undefined || max === null || max < 0) {
            if (this.isBadMax === true) {
                return;
            }
            this.isBadMax = true;

            return;
        }

        if (count === undefined || count === null || count < 0 || !Number.isInteger(count)) {
            if (this.isBadCount === true) {
                return;
            }
            this.isBadCount = true;

            return;
        }

        if (startPrice === undefined || startPrice === null || startPrice < 0) {
            if (this.isBadPrice === true) {
                return;
            }
            this.isBadPrice = true;

            return;
        }

        this.paper.emit(new Paper(name, rule, max, count, startPrice));
    }
}
