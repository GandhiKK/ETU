import {BrowserModule} from '@angular/platform-browser';
import {NgModule} from '@angular/core';
import {FormsModule} from '@angular/forms';
import {HttpClientModule} from '@angular/common/http';

import {AppComponent} from './app.component';
import {PartnersComponent} from './components/partners.component';
import {PapersComponent} from './components/papers.component';
import {SettingsComponent} from './components/settings.component';
import {PartnerModalComponent} from './components/modals/partner.modal.component';
import {PaperModalComponent} from './components/modals/paper.modal.component';
import {ChangePartnerModalComponent} from './components/modals/change.partner.modal.component';
import {ChangePaperModalComponent} from './components/modals/change.paper.modal.component';
import {InfoComponent} from './components/info.component';

@NgModule({
  declarations:
    [AppComponent, PartnersComponent, PapersComponent, SettingsComponent, PartnerModalComponent, PaperModalComponent,
      ChangePartnerModalComponent, ChangePaperModalComponent, InfoComponent],
  imports: [BrowserModule, FormsModule, HttpClientModule],
  providers: [],
  bootstrap: [AppComponent]
})

export class AppModule { }
