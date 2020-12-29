import {Component, EventEmitter, Output} from '@angular/core';

@Component({
    selector: 'app-info',
    template: `
        <div class="lab5-modal">
            <div class="modal-dialog" role="document">
                <div class="modal-content">
                    <div class="modal-header">
                        <h5 class="modal-title">Инфо</h5>
                        <button type="button" class="close" data-dismiss="modal" aria-label="Close" (click)="this.back.emit()">
                            <span aria-hidden="true">&times;</span>
                        </button>
                    </div>
                    <div class="modal-body">
                        <p>
                            <ng-content></ng-content>
                        </p>
                    </div>
                    <div class="modal-footer">
                        <button (click)="this.back.emit()" type="button" class="btn btn-primary" data-dismiss="modal">
                            Ок
                        </button>
                    </div>
                </div>
            </div>
        </div>

        <div class="lab5-backdrop"></div>`,
    providers: []
})

export class InfoComponent {
    @Output() back = new EventEmitter();
}
