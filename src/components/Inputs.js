import React, { useState } from "react";
import firebase from "../api/fbConfig";

const Inputs = () => {
  const [myTimer, setMyTimer] = useState("");
  const setTimer = () => {
    firebase.database().ref("notifs/").update({
      snoozeAlarm: myTimer,
    });
  };

  const Buzzer = () => {
    let buzzer = true;
    firebase.database().ref("notifs/").update({
      buzzer: buzzer,
    });
  };

  const Reset = () => {
    let reset = true;
    firebase.database().ref("notifs/").update({
      reset: reset,
    });
  };

  return (
    <>
      <div className="d-flex flex-column mt-3">
        <h6 className=" ">Set Snooze Alarm</h6>
        <select
          style={{}}
          value={myTimer}
          onChange={(e) => setMyTimer(e.target.value)}
        >
          <option value="05:00">05:00</option>
          <option value="10:00">10:00</option>
          <option value="15:00">15:00</option>
          <option value="20:00">20:00</option>
          <option value="25:00">25:00</option>
          <option value="30:00">30:00</option>
          <option value="35:00">35:00</option>
          <option value="40:00">40:00</option>
        </select>
      </div>
      <div className="d-flex justify-content-center mt-4 mb-5">
        <div className="d-flex mt-1 gap-3 ">
          <button onClick={Buzzer} className="btn btn-warning">
            Buzzer
          </button>
          <button onClick={setTimer} className="btn btn-success">
            Start
          </button>
          <button onClick={Reset} className="btn btn-danger">
            Reset
          </button>
        </div>
      </div>
    </>
  );
};

export default Inputs;
