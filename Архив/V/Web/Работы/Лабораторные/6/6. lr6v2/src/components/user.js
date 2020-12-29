import React from 'react';
import "./user.css"

var pr = 0;

export default class User extends React.Component{

    constructor(props){
        super(props);
        this.state = {
            username: props.username,
            brokers: props.brokers,
            stocks: props.stocks,
            count: 0,
            index: 0,
            pr: 0
        };
    }

    render() {
        return (
            <div className="User">
                <nav className="one">
                    <ul>
                        <li>{this.props.username}</li>
                        <li>Прибыль на текущий момент: {pr}</li>
                    </ul>
                </nav>

                <div className="brokers">
                    {this.get_info(this.props.username, this.props.brokers)}
                </div>
                <div className="torgs">
                    {this.get_torgs(this.props.stocks)}
                </div>
                <div className="broker">
                    <p> Продать </p>
                    <table>
                        <tr>
                            <th>id</th>
                            <th>количество</th>
                        </tr>
                        <tr>
                            <select value={this.state.index_cell} onChange={this.get_index_cell}>
                                <option value="0">0</option>
                                <option value="1">1</option>
                                <option value="2">2</option>
                            </select>
                            <th><input type = "number" min = "0" required onChange={this.get_count_cell}/></th>
                        </tr>
                    </table>
                    <button onClick={this.sell}> + </button>
                </div>
                <div className="broker">
                    <p> Купить </p>
                    <table>
                        <tr>
                            <th>id</th>
                            <th>количество</th>
                        </tr>
                        <tr>
                            <th><input type = "number" min = "0" required onChange={this.get_index_buy}/></th>
                            <th><input type = "number" min = "0" required onChange={this.get_count_buy}/></th>
                        </tr>
                    </table>
                    <button onClick={this.buy}> + </button>
                </div>
            </div>
        );
    }


    get_info(name, br) {
        for (let i = 0; i < br.length; i++) {
            if (br[i].name === name) {
                let broker = [];
                pr = br[i].money - br[i].start_money;
                broker.push(<p> Запас денежных стредств: {br[i].money} </p>);
                let table = [];
                table.push(
                    <tr>
                        <th>id</th>
                        <th>количество</th>
                        <th>стоимость</th>
                        <th>на торгах</th>
                        <th>стоимость</th>
                    </tr>
                );
                for (let j = 0; j < br[i].stocks.length; j++) {
                    table.push(
                        <tr>
                            <td>{j}</td>
                            <td>{br[i].stocks[j]}</td>
                            <td>{br[i].price[j]}</td>
                            <td> {br[i].ontorg_stocks[j]} </td>
                            <td>{br[i].ontorg_price[j]}</td>
                        </tr>
                    )
                }
                broker.push(<table>{table}</table>);
                return <div className="broker">{broker}</div>
            }
        }
    }

    get_torgs(st) {
        let table = [];
        table.push(
            <tr>
                <th>id</th>
                <th>количество</th>
                <th>цена</th>
            </tr>
        );

        for (let i = 0; i < st.length; i++) {
            table.push(
                <tr>
                    <td>{i}</td>
                    <td>{st[i].in_torg}</td>
                    <td>{st[i].price}</td>
                </tr>
            )
        }
        return <div className="broker" id="tt"><p> Акции на торгах</p><table>{table}</table></div>
    }


    sell = (event) => {
        console.log(this.state.index_cell , this.state.count_cell, this.state.username);
        /*if(this.state.index_cell < 0 || this.state.count_cell < 0 || this.state.index_cell === undefined || this.state.count_cell === undefined)
        {
          alert("Неправильный ввод")
          return
        }*/
        if(this.state.index_cell > this.state.stocks.length) {
            console.log(this.state.index_cell ,">", this.state.stocks.length);
            return;
        }
        let br = this.state.brokers;
        for (let i = 0; i < br.length; i++) {
            if (br[i].name === this.state.username) {
                if(this.state.count_cell > br[i].stocks[this.state.index_cell]) {
                    return;
                }
            }
        }
        this.props.sell(this.props.username, this.state.index_cell, this.state.count_cell);
    };

    buy = (event) => {
        console.log("зашел");
        let br = this.state.brokers;
        /*if(this.state.index_buy < 0 || this.state.count_buy < 0 || this.state.index_buy === undefined || this.state.count_buy === undefined)
        {
          alert("Неправильный ввод")
          return
        }*/

        if(this.state.index_buy > this.state.stocks.length) {
            console.log("по индексу");
            return;
        }
        for (let i = 0; i < br.length; i++) {
            if (br[i].name === this.state.username) {
                if(this.state.count_buy > this.state.stocks[this.state.index_buy].in_torg) {
                    console.log("по количеству");
                    console.log(this.state.index_buy);
                    console.log(this.state.stocks[this.state.index_buy].in_torg);
                    return;
                }
                if(br[i].money < this.state.stocks[this.state.index_buy].price * this.state.count_buy) {
                    console.log("денег нет");
                    return
                }
            }
        }
        console.log("!!!");
        this.props.buy(this.props.username, this.state.index_buy, this.state.count_buy);
    };

    get_index_cell = (event) => {
        this.setState({index_cell: Number(event.target.value)});
    };

    get_count_cell = (event) => {
        this.setState({count_cell: Number(event.target.value)});
    };

    get_index_buy = (event) => {
      this.setState({index_buy: Number(event.target.value)});
    };

    get_count_buy = (event) => {
      this.setState({count_buy: Number(event.target.value)});
    };
}
