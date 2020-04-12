package searchers;

import actors.MasterActor;
import actors.MasterActorResult;
import akka.actor.ActorRef;
import akka.actor.ActorSystem;
import akka.actor.Props;
import scala.concurrent.duration.Duration;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;

public class Searcher {
    private final List<SearchSiteInfo> infos = new ArrayList<>();

    public void AddSearchSite(SearchSiteInfo info)
    {
        infos.add(info);
    }

    public HashMap<String, String> search(String message, Duration timeout) throws ExecutionException, InterruptedException {
        ActorSystem system = ActorSystem.create("SearchSystem");

        CompletableFuture<MasterActorResult> futureResult = new CompletableFuture<>();

        try {
            ActorRef master = system.actorOf(Props.create(MasterActor.class, infos, timeout, futureResult));
            master.tell(message, ActorRef.noSender());

            return futureResult.get().result;
        } finally {
            system.terminate();
        }
    }
}
