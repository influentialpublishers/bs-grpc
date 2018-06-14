let lastMessage = ref("out of the silent planet comes a message");
let credentials = Grpc.Server.Credentials.Ssl.make(
  ~rootCert=Grpc.loadCert("./certs/ca.dev.influential.co.crt"),
  ~privateKey=Grpc.loadCert("./certs/influential-dev-server-key.pem"),
  ~certChain=Grpc.loadCert("./certs/grpc-server.dev.influential.co.crt")
);

let server =
  Grpc.Server.make(
    ~host="127.0.0.1:12345",
    ~credentials,
    ~services={
      chatService:
        Some(
          Grpc.Chat.ChatService.t(~sendMessage=(call, callback) => {
            let request = call
              |> Grpc.Chat.ChatService.SendMessageRpc.request ;
            let message = request
              |> Grpc.Chat.Message.message ;
            let replyMessage = lastMessage^;
            switch (message) {
            | None => ()
            | Some(s) => lastMessage := s
            };
            Js.log2(
              "someone invoked sendMessage:",
              message
            );
            /* Send Ack */
            let ack = Grpc.Chat.MessageAck.make(~result=Grpc.Chat.MessageAck.Message(replyMessage), ());
            Js.log2("ack=", ack);
            Js.log2("callback=", callback);
            Grpc.reply(callback, ack);
            Js.log("acked");
          }),
        ),
    },
  );
