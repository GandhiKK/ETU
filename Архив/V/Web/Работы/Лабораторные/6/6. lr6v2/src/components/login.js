import React from "react";
import "./login.css"

export default class Login extends React.Component{
    render() {
        return(
            <div className="Login">
                <form onSubmit={this.props.login}>
                    <p>Имя пользователя:</p>
                    <p id="warning">{this.props.message}</p>
                    <input name="name"/>
                    <p><button id="a">Войти</button> </p>
                </form>

            </div>
        );
    }
}
