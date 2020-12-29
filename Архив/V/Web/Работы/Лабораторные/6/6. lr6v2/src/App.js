import React from 'react';
import Login from "./components/login";
import Admin from "./components/admin"
import User from "./components/user"
import * as io from 'socket.io-client'
import './App.css';

let socket;

class App extends React.Component{
  state = {
    username: 'Nobody',
    stocks: null,
    brokers: null,
    start_exchange: false,
    message: ''
  };

  login = (event) => {
    event.preventDefault();
    let name = event.target.elements.name.value;
    console.log(name);

    socket = io('http://localhost:8080');
    socket.on('connect',function(){
      socket.emit('login', {name:name});
    });

    socket.on('welcome', (data) => {
      this.setState({username: data.uname, message: data.message});
    });

    socket.on('update', (data) => {
      this.setState({
        stocks: data.stocks,
        brokers: data.persons,
      })
    });

    socket.on('start_ex', data =>{
      this.setState({
        start_exchange: true
      });
      console.log(this.state.username, this.state.start_exchange)
    });
  };

  start_torgs = () => {
    socket.emit('start');
  };

  sell = (name, index, count) => {
    socket.emit('sell', {name:name, index:index, count:count});
  };

  buy = (name, index, count) => {
    console.log(name, index, count);
    socket.emit('buy', {name:name, index:index, count:count});
  };

  render() {
    return (
        <div className="App">
          {this.get_content()}
        </div>
    );
  }

  get_content() {
    let content;
    if (this.state.username === 'Nobody')
      content = <Login
          login={this.login}
          message = {this.state.message}
      />;
    else if (this.state.username === 'admin') {
      content = <Admin
          brokers={this.state.brokers}
          start_torgs={this.start_torgs}
      />;
    }
    else
      content = <User
          brokers={this.state.brokers}
          username ={this.state.username}
          stocks ={this.state.stocks}
          sell ={this.sell}
          buy = {this.buy}
      />;
    return content;
  }

}



export default App;
