import firebase from "firebase";

const firebaseConfig = {
  apiKey: "AIzaSyDNJYG3NWNXp3j4yf_pY9katksOhUSXkyY",
  authDomain: "moneybox-7b027.firebaseapp.com",
  databaseURL: "https://moneybox-7b027-default-rtdb.firebaseio.com",
  projectId: "moneybox-7b027",
  storageBucket: "moneybox-7b027.appspot.com",
  messagingSenderId: "369520185229",
  appId: "1:369520185229:web:8288511a53975b152d77c4",
};

firebase.initializeApp(firebaseConfig);

export default firebase;
