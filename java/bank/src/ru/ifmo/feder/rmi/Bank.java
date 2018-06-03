package ru.ifmo.feder.rmi;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.Set;

public interface Bank extends Remote {
    /* Create person (true if success, false if person with this passport exists */
    boolean createPerson(String name, String surname, String passport) throws RemoteException;

    /* Check person by passport */
    boolean checkPerson(String name, String surname, String passport) throws RemoteException;

    /* Get serializable person */
    Person getLocalPerson(String passport) throws RemoteException;

    /* Get person */
    Person getRemotePerson(String passport) throws RemoteException;

    /* Get person accounts by name */
    Set<String> getPersonAccounts(Person person) throws RemoteException;

    /* Create account by passport:id(true if created, false if was) */
    boolean createAccount(Person person, String id) throws RemoteException;

    /* Get account by passport:id(null if there is nothing) */
    Account getAccount(Person person, String id) throws RemoteException;
}