import {Component, Input} from '@angular/core';
import {PaperModalComponent} from './paper.modal.component';

@Component({
  selector: 'app-change-paper-modal',
  templateUrl: '../../templates/paperModal.html',
  providers: []
})

export class ChangePaperModalComponent extends PaperModalComponent {
  @Input() name: string;
  @Input() rule: string;
  @Input() max: number;
  @Input() count: number;
  @Input() startPrice: number;
}
