import asyncio
import websockets
import os

HOST = "0.0.0.0"
PORT = int(os.environ.get("PORT", 8765))

async def enviar_payload(websocket):
    print("ESP32 conectado")
    while True:
        with open("payload.json", "r", encoding="utf-8") as f:
            payload = f.read()
            
        await websocket.send(payload)
        print("Payload enviado:")
        print(payload)
        await asyncio.sleep(15)

async def main():
    server = await websockets.serve(
        enviar_payload,
        HOST,
        PORT
    )
    
    print(f"Servidor WebSocket rodando na porta {PORT}")
    await server.wait_closed()

asyncio.run(main())