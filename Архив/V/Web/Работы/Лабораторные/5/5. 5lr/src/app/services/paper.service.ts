import {Paper} from '../classes/Paper';

export class PaperService {
    private data: Paper[] = [];

    getData(): Paper[] {
        return this.data;
    }

    addData(title: string, rule: string, max: number, count: number, startPrice: number): void {
        this.data.push(new Paper(title, rule, max, count, startPrice));
    }

    deleteData(value: string): void {
        for (let i = 0; i < this.data.length; i++) {
            if (this.data[i].name === value) {
                this.data.splice(i, 1);
                break;
            }
        }
    }

    change(oldName: string, newName: string, rule: string, max: number, count: number, startPrice: number): void {
        for (const elem of this.data) {
            if (elem.name === oldName) {
                elem.name = newName;
                elem.rule = rule;
                elem.max = max;
                elem.count = count;
                elem.startPrice = startPrice;
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
