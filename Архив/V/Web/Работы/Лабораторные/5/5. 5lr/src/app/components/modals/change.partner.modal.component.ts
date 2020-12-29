import {Component, Input} from '@angular/core';
import {PartnerModalComponent} from './partner.modal.component';

@Component({
  selector: 'app-change-partner-modale',
  templateUrl: '../../templates/partnerModal.html',
  providers: []
})

export class ChangePartnerModalComponent extends PartnerModalComponent {
  @Input() name: string;
  @Input() money: number;
}
