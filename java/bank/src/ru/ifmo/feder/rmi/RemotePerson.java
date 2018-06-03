package ru.ifmo.feder.rmi;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class RemotePerson extends UnicastRemoteObject implements Person {
    private String name, surname;
    private String pasportId;

    public RemotePerson(String name, String surname, String pasportId, int port) throws RemoteException {
        super(port);
        this.name = name;
        this.surname = surname;
        this.pasportId = pasportId;
    }

    @Override
    public String getName() throws RemoteException {
        return name;
    }

    @Override
    public String getSurname() throws RemoteException {
        return surname;
    }

    @Override
    public String getPasportId() throws RemoteException {
        return pasportId;
    }
}
