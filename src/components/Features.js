import React, { useEffect, useState } from "react";
import Inputs from "./Inputs";
import firebase from "../api/fbConfig";

const Features = () => {
  const [twofourtimer, setTwoFourTimer] = useState();
  const [snoozetimer, setsnoozetimer] = useState();

  useEffect(() => {
    const ref = firebase.database().ref("notifs");
    ref.on("value", async (snapshot) => {
      setTwoFourTimer(snapshot.val().twofourtimer);
      setsnoozetimer(snapshot.val().snoozeAlarm);
    });
  }, []);

  return (
    <div>
      <div className="d-flex flex-column  align-items-center vh-100 vw-100 ">
        <div
          className=" myborder d-flex flex-column  justify-content-center align-items-center mt-5 "
          style={{
            backgroundColor: "#6366f1",
            width: "400px",
            height: "150px",
          }}
        >
          <h1 style={{ fontSize: "5rem" }}>{twofourtimer}</h1>
        </div>
        <div
          className=" myborder d-flex flex-column  justify-content-center align-items-center mt-3 "
          style={{
            backgroundColor: "#b91c1c",
            width: "200px",
            height: "50px",
          }}
        >
          <h4 className="text-light" style={{ fontSize: "1.5rem" }}>
            {snoozetimer}
          </h4>
        </div>
        <Inputs />
        <div
          className=" d-flex flex-column  align-items-center -center "
          style={{
            backgroundColor: "#3730a3",
            width: "100%",
            height: "300px",
            color: "white",
          }}
        >
          <h1
            className="mt-5"
            style={{
              fontSize: "4rem",
            }}
          >
            Money Box Bank
          </h1>
          <p className="fs-6 mt-5">
            Lorem, ipsum dolor sit amet consectetur adipisicing elit. Quia
            veritatis eligendi itaque voluptates veniam dolorum
          </p>
        </div>
      </div>
    </div>
  );
};

export default Features;
