import {Component, EventEmitter, Output} from '@angular/core';
import {Partner} from '../../classes/Partner';

@Component({
    selector: 'app-partner-modal',
    templateUrl: '../../templates/partnerModal.html',
    providers: []
})

export class PartnerModalComponent {
    name: string;
    money: number;

    isBadName: boolean = false;
    isBadMoney: boolean = false;

    @Output() partner = new EventEmitter<Partner>();
    @Output() closeModal = new EventEmitter();

    add(name: string, money: number): void {
        if (name === undefined || name === '' || isNaN(parseInt(name, 10)) === false) {
            if (this.isBadName === true) {
                return;
            }

            this.isBadName = true;

            return;
        }

        if (money === undefined || money === null || money < 0) {
            if (this.isBadMoney === true) {
                return;
            }

            this.isBadMoney = true;

            return;
        }

        this.partner.emit(new Partner(name, money));
    }
}
