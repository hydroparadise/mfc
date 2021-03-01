wget https://developer.download.nvidia.com/compute/cuda/11.2.1/local_installers/cuda-repo-rhel8-11-2-local-11.2.1_460.32.03-1.x86_64.rpm
sudo rpm -i cuda-repo-rhel8-11-2-local-11.2.1_460.32.03-1.x86_64.rpm
sudo dnf clean all
sudo dnf -y module install nvidia-driver:latest-dkms
sudo dnf -y install cuda
