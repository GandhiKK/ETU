import {Component, OnInit} from '@angular/core';
import {Partner} from '../classes/Partner';
import {PartnerService} from '../services/partner.service';

@Component({
  selector: 'app-partners',
  template: `
      <table class="table" *ngIf="partners.length > 0" style="width: 450px;">
          <thead>
              <tr>
                  <th scope="col">Имя</th>
                  <th scope="col">Деньги</th>
                  <th scope="col"></th>
              </tr>
          </thead>
          <tbody>
              <tr *ngFor="let element of partners">
                  <td>{{element.name}}</td>
                  <td>{{element.money}}</td>
                  <td>
                      <button (click)="changePartner($event.target)" title="Редактировать участника" class="btn btn-sm btn-primary mr-2">
                          Ред.
                      </button>
                      <button (click)="deletePartner($event.target)" title="Удалить участника" class="btn btn-sm btn-primary">
                          Удал.
                      </button>
                  </td>
              </tr>
          </tbody>
      </table>

      <div *ngIf="partners.length === 0" class="d-flex justify-content-center py-3 border-top border-bottom mb-2">
          Пусто. Добавьте участников.
      </div>

      <button (click)="add()" class="btn btn-primary">Добавить</button>

      <app-partner-modal *ngIf="addModalOpened"
                         (partner)="newPartnerEvent($event)"
                         (closeModal)="addModalOpened=false"></app-partner-modal>

      <app-change-partner-modale *ngIf="changeModalOpened"
                                 (partner)="changePartnerEvent($event)"
                                 (closeModal)="changeModalOpened=false"
                                 [name]="changeValue.name"
                                 [money]="changeValue.money"></app-change-partner-modale>

      <app-info *ngIf="infoModalOpened" (back)="infoModalOpened=false">Участник с таким именем уже есть!</app-info>`,
  providers: []
})

export class PartnersComponent implements OnInit {
  addModalOpened: boolean = false;
  changeModalOpened: boolean = false;
  changePartnerName: string;
  infoModalOpened: boolean = false;
  partners: Partner[];
  changeValue: Partner = new Partner('', 0);

  constructor(private partnerService: PartnerService) {}

  ngOnInit(): void {
      this.partners = this.partnerService.getData();
  }

  add(): void {
      this.addModalOpened = true;
  }

  newPartnerEvent(value: Partner): void {
    if (this.partnerService.find(value.name)) {
      this.infoModalOpened = true;
      return;
    }

    this.addModalOpened = false;
    this.partnerService.addData(value.name, value.money);
  }

  deletePartner(event): void {
      const name = event.closest('tr').firstChild.innerHTML;
      this.partnerService.deleteData(name);
  }

  changePartner(event): void {
    const tr = event.closest('tr');
    this.changeValue.name = tr.children[0].innerHTML;
    this.changeValue.money = tr.children[1].innerHTML;
    this.changeModalOpened = true;
    this.changePartnerName = tr.firstChild.innerHTML;
  }

  changePartnerEvent(value: Partner): void {
    this.changeModalOpened = false;
    this.partnerService.change(this.changePartnerName, value.name, value.money);
  }
}
