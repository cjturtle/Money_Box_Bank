import NavBar from "./components/NavBar";
import Features from "./components/Features";
import { BrowserRouter as Router, Route, Switch } from "react-router-dom";

function App() {
  return (
    <Router>
      <div className="App">
        <NavBar />
        <div className="content">
          <Switch>
            <Route path="/">
              <Features />
            </Route>
          </Switch>
        </div>
      </div>
    </Router>
  );
}

export default App;
