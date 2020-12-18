import {Component} from '@angular/core';

@Component({
    selector: 'app-settings',
    template: `
        <div style="width: 600px;">
            <h4>Настройки</h4>
            <div class="form-group">
                <label for="startTime">Время начала (ЧЧ:ММ):</label>
                <input type="time" id="startTime" class="form-control" [(ngModel)]="result.start">
            </div>
            <div class="form-group">
                <label for="endTime">Время окончания (ЧЧ:ММ):</label>
                <input type="time" id="endTime" class="form-control" [(ngModel)]="result.end">
            </div>
            <div class="form-group">
                <label for="intervalTime">Интервал пересчёта (ЧЧ:ММ):</label>
                <input type="time" id="intervalTime" class="form-control" [(ngModel)]="result.interval">
            </div>
        </div>`,
    providers: []
})

export class SettingsComponent {
    result: object = {
        start: '',
        end: '',
        interval: ''
    };
}
