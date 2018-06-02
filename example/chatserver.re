let server = Protobufs.Server.make();

Protobufs.Server.serverBind(
  server,
  "127.0.0.1:12345",
  Protobufs.Server.createInsecure(),
);

Protobufs.addServices(
  server,
  {
    chatService:
      Some(
        Protobufs.Chat.ChatService.t(~sendMessage=(call, callback) => {
          Js.log2(
            "someone invoked sendMessage:",
            call
            |> Protobufs.Chat.ChatService.SendMessageRpc.request
            |> Protobufs.Chat.Message.message,
          );
          /* Send Ack */
          let ack = Protobufs.Chat.MessageAck.t();
          Js.log2("ack=", ack);
          Js.log2("callback=", callback);
          callback(.
            Js.Nullable.null,
            ack,
            Js.Nullable.undefined,
            Js.Nullable.undefined,
          );
          Js.log("acked");
        }),
      ),
  },
);

Protobufs.Server.start(server);
