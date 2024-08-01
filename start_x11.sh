# Arquivo para configurar e iniciar o servidor x11 no linux
export DISPLAY=$(grep -oP "(?<=nameserver\s)[\d.]+" /etc/resolv.conf | head -n 1):0
pkill -f vcxsrv
echo "VcXsrv deve estar iniciado e configurado para aceitar conexões."
sleep 5
echo "Ambiente X11 configurado e pronto para execução do projeto."