import {Partner} from '../classes/Partner';

export class PartnerService {
    private data: Partner[] = [];

    getData(): Partner[] {
        return this.data;
    }

    addData(title: string, money: number): void {
        this.data.push(new Partner(title, money));
    }

    deleteData(value: string): void {
        for (let i = 0; i < this.data.length; i++) {
            if (this.data[i].name === value) {
                this.data.splice(i, 1);
                break;
            }
        }
    }

    change(oldName: string, newName: string, money: number) {
        for (const elem of this.data) {
            if (elem.name === oldName) {
                elem.name = newName;
                elem.money = money;
                break;
            }
        }
    }

    length(): number {
        return this.data.length;
    }

    find(value: string): boolean {
        for (const elem of this.data) {
            if (elem.name === value) {
                return true;
            }
        }

        return false;
    }
}
