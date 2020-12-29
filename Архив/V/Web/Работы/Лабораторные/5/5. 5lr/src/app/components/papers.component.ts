import {Component, OnInit} from '@angular/core';
import {PaperService} from '../services/paper.service';
import {Paper} from '../classes/Paper';

@Component({
    selector: 'app-papers',
    template: `
        <table class="table" style="width: 1300px;" *ngIf="papers.length > 0">
            <thead>
            <tr>
                <th scope="col">Фирма</th>
                <th scope="col">Правило изменения</th>
                <th scope="col">Максимальное значение для изменения</th>
                <th scope="col">Количество</th>
                <th scope="col">Начальная стоимость одной акции</th>
                <th scope="col">Функции</th>
            </tr>
            </thead>
            <tbody>
            <tr *ngFor="let element of papers">
                <td>{{element.name}}</td>
                <td>{{element.rule}}</td>
                <td>{{element.max}}</td>
                <td>{{element.count}}</td>
                <td>{{element.startPrice}}</td>
                <td>
                    <button (click)="changePaper($event.target)" title="Редактировать акцию" class="btn btn-sm btn-primary mr-2">
                        Ред.
                    </button>
                    <button (click)="deletePaper($event.target)" title="Удалить акцию" class="btn btn-sm btn-primary">
                        Удал.
                    </button>
                </td>
            </tr>
            </tbody>
        </table>

        <div *ngIf="papers.length === 0" class="d-flex justify-content-center py-3 border-top border-bottom mb-2">
            Пусто. Добавьте акции.
        </div>

        <button (click)="add()" class="btn btn-primary">
            Добавить
        </button>

        <app-paper-modal *ngIf="addModalOpened"
                         (paper)="newPaperEvent($event)"
                         (closeModal)="this.addModalOpened=false">
        </app-paper-modal>

        <app-change-paper-modal *ngIf="changeModalOpened"
                                (closeModal)="changeModalOpened=false"
                                (paper)="changePaperEvent($event)"
                                [name]="changeValue.name"
                                [rule]="changeValue.rule"
                                [max]="changeValue.max"
                                [count]="changeValue.count"
                                [startPrice]="changeValue.startPrice">
        </app-change-paper-modal>

        <app-info *ngIf="infoModalOpened" (back)="infoModalOpened=false">Акция с таким именем уже есть!</app-info>`,
    providers: []
})

export class PapersComponent implements OnInit {
    addModalOpened: boolean = false;
    changeModalOpened: boolean = false;
    changePaperName: string;
    infoModalOpened: boolean = false;
    papers: Paper[];
    changeValue: Paper = new Paper('', '', 0, 0, 0);

    constructor(private paperService: PaperService) {}

    ngOnInit(): void {
        this.papers = this.paperService.getData();
    }

    add(): void {
        this.addModalOpened = true;
    }

    newPaperEvent(value: Paper): void {
        if (this.paperService.find(value.name)) {
            this.infoModalOpened = true;
            return;
        }
        this.addModalOpened = false;
        this.paperService.addData(value.name, value.rule, value.max, value.count, value.startPrice);
    }

    deletePaper(event): void {
        const deleteValue = event.closest('tr').firstChild.innerHTML;
        this.paperService.deleteData(deleteValue);
    }

    changePaper(event): void {
        const tr = event.closest('tr');
        this.changeValue.name = tr.children[0].innerHTML;
        this.changeValue.rule = tr.children[1].innerHTML;
        this.changeValue.max = tr.children[2].innerHTML;
        this.changeValue.count = tr.children[3].innerHTML;
        this.changeValue.startPrice = tr.children[4].innerHTML;
        this.changeModalOpened = true;
        this.changePaperName = tr.firstChild.innerHTML;
    }

    changePaperEvent(value: Paper): void {
        this.changeModalOpened = false;
        this.paperService.change(this.changePaperName, value.name, value.rule, value.max, value.count, value.startPrice);
    }
}
