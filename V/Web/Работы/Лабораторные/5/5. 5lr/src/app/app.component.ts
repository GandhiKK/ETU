import {Component, ViewChild} from '@angular/core';
import {HttpClient} from '@angular/common/http';
import {PartnerService} from './services/partner.service';
import {PaperService} from './services/paper.service';
import {SettingsComponent} from './components/settings.component';

@Component({
    selector: 'app-root',
    template: `
        <div class="d-flex flex-column justify-content-center align-items-center vh-100">
            <h2>Биржа акций</h2>
            <button (click)="start()" *ngIf="pageNum === 0" class="btn btn-primary">
                <b>Начать настройку</b>
            </button>
            <div *ngIf="pageNum === 1">
                <app-partners></app-partners>
                <button (click)="toSecondPage()" class="btn btn-primary ml-2">
                    Продолжить
                </button>
            </div>
            <div *ngIf="pageNum === 2">
                <app-papers></app-papers>
                <button (click)="toThirdPage()" class="btn btn-primary ml-2">
                    Продолжить
                </button>
            </div>
            <div *ngIf="pageNum === 3">
                <app-settings></app-settings>
                <button (click)="toEnd()" class="btn btn-primary ml-2">
                    Завершить
                </button>
            </div>
            <div *ngIf="pageNum === 4">
                <p>{{finishText}}</p>
            </div>
            <p>Страница {{pageNum+1}}/5</p>
            <app-info *ngIf="infoModalOpened" (back)="infoModalOpened=false">{{messageInfo}}</app-info>
        </div>`,
    providers: [PartnerService, PaperService]
})

export class AppComponent {
    pageNum: number = 0;
    infoModalOpened: boolean = false;
    messageInfo: string;

    finishText: string = '';

    @ViewChild(SettingsComponent, {static: false}) viewChild: SettingsComponent;

    constructor(private partnerService: PartnerService, private paperService: PaperService, private http: HttpClient) {}

    start(): void {
        this.pageNum++;
    }

    toSecondPage(): void {
        if (this.partnerService.length() === 0) {
            this.messageInfo = 'Нет ни одного участника!';
            this.infoModalOpened = true;
            return;
        }

        this.pageNum++;
    }

    toThirdPage(): void {
        if (this.paperService.length() === 0) {
            this.messageInfo = 'Нет ни одной акции!';
            this.infoModalOpened = true;
            return;
        }

        this.pageNum++;
    }

    toEnd(): void {
        // @ts-ignore
        if (this.viewChild.result.start === '' || this.viewChild.result.end === '' || this.viewChild.result.interval === '') {
            this.messageInfo = 'Заданы не все настройки!';
            this.infoModalOpened = true;
            return;
        }
        this.pageNum++;
        this.req();
    }

    req(): void {
        this.http.post('http://localhost:3000/print', {
            partners: this.partnerService.getData(),
            papers: this.paperService.getData(),
            settings: this.viewChild.result
        }).subscribe((data) => {
            console.log(data);
            this.finishText = 'Настройки сохранены в JSON файл!';
        }, (err) => {
            console.log(err);
            this.finishText = 'Произошла ошибка';
        });
    }
}
